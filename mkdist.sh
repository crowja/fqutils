if test z$1 = z; then
  LDFLAGS=-L/usr/local/lib ./autogen.sh && LDFLAGS=-L/usr/local/lib make distcheck
else
  PREDIST=1 LDFLAGS=-L/usr/local/lib ./autogen.sh && LDFLAGS=-L/usr/local/lib make distcheck
fi

