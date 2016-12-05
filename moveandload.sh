cp ./u-boot.sb ../mxsldr/u-boot.sb
./tools/mxsboot nand u-boot.sb u-boot.nand
cp ./u-boot.nand /tftpboot/u-boot.nand
sudo ../mxsldr/mxsldr u-boot.sb