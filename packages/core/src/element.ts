import 'reflect-metadata';
import fs from 'node:fs';
import path from 'node:path';

import { Constructor } from './constructor';

export interface ElementOptions {
  readonly select: string | Array<string>;
  readonly template?: string;
  readonly templateUrl?: string;
  readonly styles?: string | Array<string>;
  readonly stylesUrl?: string;
  readonly attributes?: Record<string, string | Array<string>>;
}

export interface ElementMeta {
  readonly select: string | Array<string>;
  readonly template: string;
  readonly styles: string | Array<string>;
  readonly attributes: Record<string, string | Array<string>>;
}

export function Element(options: ElementOptions) {
  return <T extends Constructor>(Base: T) => {
    let template = options.template;

    if (options.templateUrl) {
      template = fs.readFileSync(path.resolve(module.parent?.path || '', options.templateUrl)).toString();
    }

    if (!template) {
      throw new Error('a template is required');
    }

    let styles = options.styles;

    if (options.stylesUrl) {
      styles = fs.readFileSync(path.resolve(module.parent?.path || '', options.stylesUrl)).toString();
    }

    if (!styles) {
      throw new Error('a style is required');
    }

    const meta: ElementMeta = {
      select: options.select,
      template: template!,
      styles: styles!,
      attributes: options.attributes || { }
    };

    Reflect.defineMetadata('__$meta__', meta, Base);
    return Base;
  };
}
