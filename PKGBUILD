pkgname=backlight
pkgver=1.0.0
pkgrel=1
pkgdesc="Backlight util"
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url='https://github.com/entwanne/backlight'
options=(!debug)
license=('MIT')
depends=('python')
makedepends=('gcc')
source=(
    'backlight'
    'set-backlight-raw.c'
)
sha256sums=(
    'ea5ab828996dd379bde7fc767abf5aa10edd15c9c6804ca8d2537de25e28b479'
    '685e4955083ed990f8d2ddbf71013bbbe67528c2f747aaf7e8d3551e36b26a40'
)

build() {
  gcc -o set-backlight-raw set-backlight-raw.c
}

package() {
  install -Dm4755 "set-backlight-raw" "${pkgdir}/usr/bin/set-backlight-raw"
  install -Dm755 "backlight" "${pkgdir}/usr/bin/backlight"
}
