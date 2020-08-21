#!/bin/bash
## This will only work on MACOS with a geant4 installed via homebrew (and also, if you haven't mingled the brew's install path)

CURDIR=$(pwd)
GEANTPATH=/usr/local/bin
GEANTSOURCEME=${GEANTPATH}/geant4.sh
GEANTSOURCEME_RESOLVED=$(readlink ${GEANTSOURCEME})
GEANTPATH_RESOLVED=$(dirname ${GEANTSOURCEME_RESOLVED})

if [[ -e ${GEANTSOURCEME_RESOLVED} ]]
then;
    echo "$GEANTSOURCEME doesn't exist, exiting"
    return
fi

cd $GEANTPATH
source $GEANTSOURCEME
cd $CURDIR
