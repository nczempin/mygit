from hashlib import sha1
def githash(data):
    s = sha1()
    s.update("blob %u\0" % len(data))
    s.update(data)
    return s.hexdigest()
print (githash("foobar\n"))
