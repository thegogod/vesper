import 'reflect-metadata';

import { HelloWorld } from './testing/hello-world';
import { ElementMeta } from './element';

describe('Element', () => {
  it('should load multi-file', () => {
    const meta: ElementMeta = Reflect.getOwnMetadata('__$meta__', HelloWorld);

    expect(meta).toBeDefined();
    expect(meta.select).toEqual('hello-world');
    expect(meta.template).toEqual('<p>hello world</p>\n');
    expect(meta.attributes).toEqual({ class: 'hello-world' });
    expect(meta.styles).toEqual([
      '.hello-world {',
      '  display: block;',
      '}',
      ''
    ].join('\n'));
  });
});
