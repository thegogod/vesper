import { Element } from '../../element';

@Element({
  select: 'hello-world',
  templateUrl: './hello-world.html',
  stylesUrl: './hello-world.css',
  attributes: { class: 'hello-world' }
})
export class HelloWorld implements Element {
  onInit() {
    console.log('hello-world: init');
  }

  onDestory() {
    console.log('hello-world: destroy');
  }
}
