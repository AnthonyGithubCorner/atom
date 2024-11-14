
IF START
setRotate( -90 )

selectAnim( idle )
FUNC stopr
SET STOPPING
changeX( -0.001 )
ONQUIT
CLEAR STOPPING
ENDONQUIT
ENDFUNC

FUNC stopl
changeX( 0.001 )
ONQUIT
CLEAR STOPPING
ENDONQUIT
ENDFUNC

FUNC moveright
changeX( 0.04 )
IF STOPRIGHT
SET NOTMOVING
EXCIN stopr constant 10 10
CLEAR STOPRIGHT
CLEAR STOPPING
QUITFUNC
ENDIF
ENDFUNC


FUNC moveleft
changeX( -0.04 )
IF STOPLEFT
SET NOTMOVING 
CLEAR STOPLEFT
EXCIN stopl constant 10 10
QUITFUNC
ENDIF
ENDFUNC

SET NOTMOVING

FUNC anim
nextFrame( )
IF NOTMOVING
selectAnim( idle )
QUITFUNC
ENDIF
ONQUIT
enableRender( player )
CLEAR ANIMRUNNING
ENDONQUIT

ENDFUNC

CLEAR START
ENDIF

IF !KEYD
SET STOPRIGHT
ENDIF

IF !KEYA
SET STOPLEFT
ENDIF



IF NOTMOVING AND KEYD
IF !STOPPING
CLEAR STOPRIGHT
CLEAR NOTMOVING
setRotate( 180 )
selectAnim( run )
EXCIN anim constant -1 10
EXCIN moveright constant -1 1
ENDIF
ENDIF

IF NOTMOVING AND KEYA
IF !STOPPING
CLEAR STOPLEFT
CLEAR NOTMOVING
setRotate( 0 )
selectAnim( run )
EXCIN anim constant -1 10
EXCIN moveleft constant -1 1
ENDIF
ENDIF