import sensor, image, time
from pyb import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.VGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must turn this off to prevent image washout...
clock = time.clock()
uart = UART(3, 9600)

blueThreshold = [10, 60, -20, 10, -55, -25] # blue 3
redThreshold = [0, 50, 10, 65, 10, 45] # red 1
greenThreshold = [20, 95, -65, -30, 30, 55] # green 2
servo5DirectionAngle = [];

def scanQRCode():
    while(True):
        # may add some code to control servo motions
        img = sensor.snapshot()
        img.lens_corr(1.8) # strength of 1.8 is good for the 2.8mm lens.
        for code in img.find_qrcodes():
            return code.payload()

def reachForTarget(color):
    targetThreshold = [];
    if(color == 1):
        targetThreshold = redThreshold;
    elif(color == 2):
        targetThreshold = greenThreshold;
    else:
        targetThreshold = blueThreshold;
    # turn machine arm to have the target in the middle of the camera
    while(True):
        img = sensor.snapshot()
        blobs = img.find_blobs([targetThreshold], pixels_threshold=200, area_threshold=200, merge=True)
        cxSum = 0
        for b in blobs:
            cxSum += b.cx()
        cxAverage = cxSum / len(blobs)
        if csAverage == 160:
            break
        else:
            uart.write('N')

    # move forward to have the target in the right distance

    # catch
    uart.write('D')
    # move backward

    # normal state


    #uart.write();

order1 = [];
order2 = [];

#while(True):
    #clock.tick()
    #img = sensor.snapshot()
    #order1Str, order2Str = scanQRCode().split('+')
    ##order1 = list(map(lambda x: int(x), list(order1Str)))
    ##order2 = list(map(lambda x: int(x), list(order2Str)))
    #order1 = list(order1Str)
    #order2 = list(order2Str)
    #print("order1: {}".format(order1))
    #print("order2: {}".format(order2))
    ##uart.write(order1[0])
    ##uart.write(order1[1])
    ##uart.write(order1[2])
    ##uart.write(order2[0])
    ##uart.write(order2[1])
    ##uart.write(order2[2])


while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    if(uart.any()):
        message = uart.read().decode('utf-8')
        print(message)
        if(message == 'qrcode'):
            order1Str, order2Str = scanQRCode().split('+');
            #order1 = list(map(lambda x: int(x), list(order1Str)))
            #order2 = list(map(lambda x: int(x), list(order2Str)))
            order1 = list(order1Str)
            order2 = list(order2Str)
            print("order1: {}".format(order1))
            print("order2: {}".format(order2))
            #uart.write(order1[0])
            #uart.write(order1[1])
            #uart.write(order1[2])
            #uart.write(order2[0])
            #uart.write(order2[1])
            #uart.write(order2[2])
        elif(message == 'findColor'):
            for i in order1:

                reachForTarget(i)
            for i in order2:
                pass


