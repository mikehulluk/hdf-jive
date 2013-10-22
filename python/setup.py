import os
from setuptools import setup

# Utility function to read the README file.
# Used for the long_description.  It's nice, because now 1) we have a top level
# README file and 2) it's easier to type in the README file than to put a raw
# string in below ...
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

setup(
    name = "hdfjive",
    version = "0.0.0.1-alpha",
    author = "Mike Hull",
    author_email = "mikehulluk@gmail.com",
    description = ("Library for storing, selecting and plotting traces from neuronal simulations"),
    license = "BSD",
    url = "https://github.com/mikehulluk/mreorg",

    package_dir = {'':'src' },
    packages=['hdfjive',
              #'mreorg.dependancies',
              ],
    # Could also have been done with 'scripts=':
    entry_points = {
        'console_scripts': [
            'hdfjive = hdfjive.cmdline.cmdline:main',
        ],
    },

    package_data={
        'mreorg':[
            #'curator/frontend/templates/*.html',
            ##'curator/frontend/static/*',
            #'curator/frontend/static/javascript/*',
            #'curator/frontend/static/customcss/*',
            #'curator/frontend/static/javascript-moment/*',
            #'curator/frontend/static/sphinx/*',
            ]
        },


    #data_files=[
    #    ('mreorg/etc', ['etc/configspec.ini']),
    #            #('config', ['cfg/data.cfg']),
    #            #('/etc/init.d', ['init-script'])
    #            ],


    install_requires=[],

    long_description=read('README.txt'),
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Topic :: Utilities",
        "License :: OSI Approved :: BSD License",
    ],
)

