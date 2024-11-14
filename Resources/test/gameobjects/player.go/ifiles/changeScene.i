

IF checkTrigger( box2 ) AND IN_BG1
switchScene( bg2 )
CLEARG IN_BG1
SET IN_BG2
ENDIF

IF checkTrigger( box2 ) AND IN_BG2
switchScene( bg1 )
CLEARG IN_BG2
SETG IN_BG1
ENDIF