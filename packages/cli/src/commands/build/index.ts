import fs from 'node:fs';
import path from 'node:path';

import * as tsup from 'tsup';
import { CommandModule } from 'yargs';

interface Args {
  readonly path: string;
}

export const build: CommandModule<{ }, Args> = {
  command: 'build <path>',
  aliases: 'b',
  describe: 'build a project',
  builder: (b) => {
    return b.positional('path', {
      alias: 'p',
      type: 'string',
      describe: 'path to the project directory',
      demandOption: true
    });
  },
  handler: async (args) => {
    const srcDir = path.join(args.path, 'src');
    const outDir = path.join(args.path, 'dist');

    await tsup.build({
      bundle: true,
      dts: true,
      minify: true,
      sourcemap: true,
      treeshake: true,
      splitting: true,
      clean: true,
      platform: 'browser',
      target: 'es2015',
      outDir,
      entry: [path.join(srcDir, 'index.ts')]
    });

    fs.copyFileSync(
      path.join(srcDir, 'index.html'),
      path.join(outDir, 'index.html')
    );
  }
};
