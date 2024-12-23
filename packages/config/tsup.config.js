/** @type {import('tsup').Options} */
module.exports = {
  bundle: true,
  dts: true,
  minify: true,
  sourcemap: true,
  treeshake: true,
  splitting: true,
  clean: true,
  platform: 'browser',
  target: 'es2015',
  outDir: 'dist',
  entry: ['src/index.ts']
};
