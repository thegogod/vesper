import 'reflect-metadata';

import { Constructor } from './constructor';

export interface ElementOptions {
  readonly name: string;
  readonly template?: string;
  readonly style?: string;
  readonly attributes?: Record<string, string | Array<string>>;
}

export interface Element {
  onMount?(): void | Promise<void>;
  onUnmount?(): void | Promise<void>;
  onChange?(): void | Promise<void>;
}

export function Element(options: ElementOptions) {
  return <T extends Constructor>(Base: T) => {
    Reflect.defineMetadata('__$element__', options, Base);
    return Base;
  };
}
