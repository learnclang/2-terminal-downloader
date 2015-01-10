"""Download file from a terminal

Contents:
    - Communicating via HTTP
    - Opening a file
    - Writing to a file

Usage:
    $ lc_download.py http://google.com

"""

import os
import urllib2


def download(url):
    """Download into ram, then disk"""
    response = urllib2.urlopen(url)
    destination = os.path.basename(url)
    with open(destination, "wb") as f:
        f.write(response.read())


if __name__ == '__main__':
    import sys

    try:
        url = sys.argv[1]
    except:
        print "Please enter a URL"
        sys.exit()

    download(url)
