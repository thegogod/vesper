import { Element } from '../../element';

@Element({
  select: 'foo-bar',
  template: `<p>foo bar</p>`,
  styles: `.foo-bar { display: block; }`,
  attributes: { class: 'foo-bar' }
})
export class FooBar implements Element {
  onInit() {
    console.log('foo-bar: init');
  }

  onDestory() {
    console.log('foo-bar: destroy');
  }
}
