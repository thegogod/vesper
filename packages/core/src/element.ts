import 'reflect-metadata';

import { Constructor } from './constructor';
import * as mixins from './mixins';

export interface ElementOptions {
  readonly name: string;
  readonly template?: string;
  readonly style?: string;
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
    Reflect.defineMetadata('__$element__', options, Base);

    class _Element extends HTMLElement {
      constructor() {
        super();
        const root = this.attachShadow({ mode: 'open' });
        root.innerHTML = [
          '<style>', options.style || '', '</style>',
          options.template || ''
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
    customElements.define(options.name, _Element);
    return _Element;
  };
}
