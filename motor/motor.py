import serial
from matplotlib import pyplot
from matplotlib.animation import FuncAnimation

# use serial port to communicate with Teensy
ard = serial.Serial('/dev/ttyACM0',192000,timeout=5)

fig,ax = pyplot.subplots(figsize=(8,4))
hallA = [0 for n in range(512)]
hallB = [0 for n in range(512)]
horiz = [n for n in range(512)]
ln1,=pyplot.plot(hallA,horiz,'red',label='Hall A')
ln2,=pyplot.plot(hallB,horiz,'blue',label='Hall B')

def init():
    ax.set(xlim=(0,511),ylim=(0,16000//64))
    pyplot.xticks([0,100,200,300,400,500],[0,10,20,30,40,50])
    pyplot.xlabel('time (ms)')
    pyplot.ylabel('Hall sensor')
    pyplot.legend()
    return ln1,ln2,

def update(i):
    ard.write(b'g\n')
    for n in range(512):
        message = ard.readline()
        value = 0
        for i in range(len(message)-2):
            if message[i]==32:
                hallA[n] = value
                value = 0
            else:
                value = 10*value+message[i]-48
        hallB[n] = value
    ln1.set_data(horiz,hallA)
    ln2.set_data(horiz,hallB)
    return ln1,ln2,

ani = FuncAnimation(fig,update,init_func=init)
pyplot.show()
