IF START
selectAnim( spinning )
CLEAR START
CLEAR ANIMRUNNING
ENDIF

FUNC anim
nextFrame( )
ONQUIT
CLEAR ANIMRUNNING
ENDONQUIT
ENDFUNC

IF !ANIMRUNNING
EXCIN anim constant -1 100
SET ANIMRUNNING
ENDIF