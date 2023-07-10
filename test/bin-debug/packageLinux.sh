#!/bin/sh
set -x

[ ! -e ../../config.sh ] && die "FRESteamWorks/config.sh is not set up!"
. ../../config.sh

ANE_PATH=../../lib/bin

rm -rf FRESteamWorksTestApp

cp "$STEAM_SDK/redistributable_bin/linux64/libsteam_api.so" .

# Generate cert on the fly
"$AIR_SDK/bin/adt" -certificate -cn MyCertificateName 2048-RSA \
                   CertificateTest.p12 test


"$AIR_SDK"/bin/adt -package -XnoAneValidate -tsa none -storetype pkcs12 \
                   -keystore CertificateTest.p12 -storepass test \
                   -target bundle FRESteamWorksTest FRESteamWorksTest-app.xml \
                   FRESteamWorksTest.swf \
                   libsteam_api.so steam_appid.txt \
                   -extdir "$ANE_PATH"

rm -f libsteam_api.so
