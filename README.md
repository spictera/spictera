Sample code to get GEO location data from Linux and Windows services

```
$ sudo apt install libgeoclue-2-dev libgeoclue-2-0 libdbus-1-dev libglib2.0-dev make gcc
$ make
$ getlocation
```

Add spictera to whitelist in geoclue.conf

```
$ sudo vi /etc/geoclue/geoclue.conf

whitelist=spictera
[spictera]
allowed=true
system=true
users=

url=https://www.googleapis.com/geolocation/v1/geolocate?key=YOURKEY
```

Restart service

```
$ sudo systemctl restart geoclue
```

<!---
spictera/spictera is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
