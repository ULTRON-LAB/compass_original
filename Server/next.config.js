/** @type {import('next').NextConfig} */
const nextConfig = {
  output: 'export',
  // productionBrowserSourceMaps: true,
  // Put other setting here
  // webpack: (config, { isServer }) => {
  //   if (!isServer) {
  //     Object.assign(config.resolve.alias, {
  //       'react': 'preact/compat',
  //       'react-dom/test-utils': 'preact/test-utils',
  //       'react-dom': 'preact/compat',
  //     })
  //   }
  //   return config
  // },
}
module.exports = nextConfig