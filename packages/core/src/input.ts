import 'reflect-metadata';

export function Input() {
  return (_target: any, _key: string, descriptor: PropertyDescriptor) => {
    Reflect.defineMetadata('__$input__', null, descriptor);
  };
}
