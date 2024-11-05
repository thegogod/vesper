// import { faker } from '@faker-js/faker';
import mqtt from 'mqtt';

(async () => {
  const client = mqtt.connect('tcp://localhost:1883');

  client.on('connect', () => {
    console.info('connected...');
  });

  client.on('message', (topic, payload) => {
    console.info(topic, payload.toString('utf8'));
  });
})();
