

IF START
setX( 0.8 )
setY( 0.5 )
selectAnim( popup )
CLEAR ANIMRAN
CLEAR START

FUNC anim
nextFrame( )

IF !CANSTARTDIALOGUE
CLEAR ANIMRUNNING
QUITFUNC
ENDIF

ONQUIT
CLEAR ANIMRUNNING
ENDONQUIT
ENDFUNC

ENDIF





IF CANSTARTDIALOGUE AND !ANIMRAN
SET ANIMRUNNING
SET ANIMRAN
EXCIN anim constant 19 100
ENDIF

IF !CANSTARTDIALOGUE AND !ANIMRUNNING
CLEAR ANIMRAN
selectAnim( popup )
ENDIF