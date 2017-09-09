from morse.builder import *

from math import pi

#SOI
quad = QUAD2012()

#init
quad.translate(x=0.0, z=0.0)
#quad.rotate(z=pi/3)

#Sensors
semanticC = SemanticCamera()
semanticC.translate(x=0.0, z=-0.0)
semanticC.rotate(x=+0.2)
quad.append(semanticC)
semanticC.properties(Vertical_Flip=False)

#pose = Pose()
#quad.append(pose)
#pose.add_stream('socket')
#pose.add_service('socket')

#Actuator
#rotorcraftattitude = RotorcraftAttitude()
#quad.append(rotorcraftattitude)
#rotorcraftattitude.add_service('socket')

#Actuator
teleport = Teleport()
quad.append(teleport)
teleport.add_stream('socket')
teleport.add_service('socket')

#Environment
env = Environment('land-1/trees')
env.set_camera_location([10.0, -10.0, 10.0])
env.set_camera_rotation([1.0470, 0, 0.7854])
env.select_display_camera(semanticC)
