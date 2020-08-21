#!/bin/bash
## This will only work on MACOS with a geant4 installed via homebrew (and also, if you haven't mingled the brew's install path)

CURDIR=$(pwd)
GEANTSOURCEME=/usr/local/bin/geant4.sh
GEANTSOURCEME_RESOLVED=/usr/local/bin/$(readlink ${GEANTSOURCEME})
GEANTPATH_RESOLVED=$(dirname ${GEANTSOURCEME_RESOLVED})

if [[ ! -e ${GEANTSOURCEME_RESOLVED} ]]
then;
    echo "$GEANTSOURCEME doesn't exist, exiting"
    return
fi

cd $GEANTPATH_RESOLVED
source $GEANTSOURCEME_RESOLVED
cd $CURDIR
