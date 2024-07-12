Sample code to get GEO location data from Linux and Windows services

```
$ sudo apt install libgeoclue-2-dev libgeoclue-2-0 libdbus-1-dev libglib2.0-dev make gcc
$ make
$ getlocation
```
```
sudo apt install meson
sudo apt install modemmanager-dev
sudo apt install libavahi-client-dev
sudo apt install libavahi-glib-dev
sudo apt install libnotify-dev

sudo apt install libjson-glib-dev
sudo apt install libsoup-3.0-dev
sudo apt install libmm-glib-dev
sudo apt install libgirepository1.0-dev
sudo apt install valac
sudo apt install gettext
sudo apt install gtk-doc-tools

meson --prefix=/usr --sysconfdir/etc -Ddbus-srv-user=geoclue build

ninja -C build
sudo ninja -C build install
```

```
cat /etc/passwd | grep "geoclue"
sudo chsh geoclue -s /bun/bash
```
```
copy .conf file /etc/geoclue/geoclue.conf
sudo cp geoclue.conf ...
```
```
sudo systemctl restart geoclue
sudo systemctl daemon-reload
```
Add spictera to whitelist in geoclue.conf

```
$ sudo vi /etc/geoclue/geoclue.conf

whitelist=spictera
[spictera]
allowed=true
system=true
users=

url=https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyAOwOJTh28qDqPyJe_I6C17SjodtPOo_KM
```

Restart service

```
$ sudo systemctl restart geoclue
```

<!---
spictera/spictera is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
