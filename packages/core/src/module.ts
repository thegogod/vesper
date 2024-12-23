import 'reflect-metadata';

import { Constructor } from './constructor';

export interface ModuleOptions {
  readonly imports?: Array<any>;
  readonly exports?: Array<any>;
}

export function Module(options: ModuleOptions) {
  return <T extends Constructor>(Base: T) => {
    Reflect.defineMetadata('__$module__', options, Base);
    return Base;
  };
}
