
FUNC moveright
changeX( 0.001 )
IF ARELEASED
SET NOTMOVING
CLEAR ARELEASED
QUITFUNC
ENDIF
ENDFUNC

FUNC moveleft
changeX( -0.001 )
ENDFUNC

IF START
SET NOTMOVING
CLEAR START
ENDIF

IF NOTMOVING AND APRESSED
CLEAR NOTMOVING
EXCIN moveright constant -1 10
ENDIF

CLEAR APRESSED