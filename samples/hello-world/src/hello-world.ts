import { Element } from '@vesper/core';

@Element({
  name: 'hello-world',
  template: `<p>hello, world</p>`,
  style: `
    .hello-world {
      display: block;
    }
  `,
  attributes: { class: 'hello-world' }
})
export class HelloWorld {
  onMount() {
    console.log('mounted');
  }

  onUnMount() {
    console.log('unmounted');
  }
}
