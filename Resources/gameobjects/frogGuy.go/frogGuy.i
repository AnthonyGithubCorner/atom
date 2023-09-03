IF START
setRotate( 0 )
CLEAR ENDDIALOGUE
disableRender( frogGuy )
setX( 0.3 )
setY( 0.1 )
CLEAR START
ENDIF

IF GSTARTDIALOGUE
renderDialogue( test_idea )
enableRender( frogGuy )
ENDIF

IF KEYR AND GSTARTDIALOGUE
SET ENDDIALOGUE
ENDIF

IF GSTARTDIALOGUE
disableRender( player )
disableActions( player )
disableRender( bg )
disableRender( orb )
ENDIF

IF ENDDIALOGUE
# set back to start of dialogue
changeLine( 1 )
enableRender( bg )
enableRender( orb )
enableRender( player )
enableActions( player )
disableRender( frogGuy )
CLEARG GSTARTDIALOGUE
CLEAR ENDDIALOGUE
ENDIF