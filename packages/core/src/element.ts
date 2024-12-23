import 'reflect-metadata';
import fs from 'node:fs';
import path from 'node:path';

import { Constructor } from './constructor';
import * as mixins from './mixins';

export interface ElementOptions {
  readonly select: string | Array<string>;
  readonly template?: string;
  readonly templateUrl?: string;
  readonly styles?: string | Array<string>;
  readonly stylesUrl?: string;
  readonly attributes?: Record<string, string | Array<string>>;
}

export interface Element {
  onInit?(): void | Promise<void>;
  onMount?(): void | Promise<void>;
  onUnMount?(): void | Promise<void>;
  onDestroy?(): void | Promise<void>;
}

export function Element(options: ElementOptions) {
  return <T extends Constructor>(Base: T) => {
    let template: string | undefined;
    let style: string | undefined;

    Reflect.defineMetadata('__$element__', options, Base);

    if (options.templateUrl) {
      template = fs.readFileSync(path.resolve(module.parent?.path || '', options.templateUrl)).toString();
    }

    if (!template) {
      throw new Error('a template is required');
    }

    if (options.stylesUrl) {
      style = fs.readFileSync(path.resolve(module.parent?.path || '', options.stylesUrl)).toString();
    }

    class _Element extends HTMLElement {
      constructor() {
        super();
        const root = this.attachShadow({ mode: 'open' });
        root.innerHTML = [
          '<style>', style, '</style>',
          template
        ].join('\n');

        for (const [name, value] of Object.entries(options.attributes || { })) {
          if (typeof value === 'string') {
            this.setAttribute(name, value);
          } else {
            this.setAttribute(name, value.join(' '));
          }
        }
      }
    };

    mixins.apply(_Element, Base);
    Reflect.set(_Element, 'name', Base.name);

    if (typeof options.select === 'string') {
      customElements.define(options.select, _Element);
    } else {
      for (const select of options.select) {
        customElements.define(select, _Element);
      }
    }

    return _Element;
  };
}
