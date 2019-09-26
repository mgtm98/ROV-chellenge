import traceback
import sys

import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GObject


# Initializes Gstreamer, it's variables, paths
Gst.init(sys.argv)


def on_message(bus, message, loop):
    mtype = message.type
    """
        Gstreamer Message Types and how to parse
        https://lazka.github.io/pgi-docs/Gst-1.0/flags.html#Gst.MessageType
    """
    if mtype == Gst.MessageType.EOS:
        print("End of stream")
        
    elif mtype == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        print(err, debug)     
    elif mtype == Gst.MessageType.WARNING:
        err, debug = message.parse_warning()
        print(err, debug)             
        
    return True 


pipeline = Gst.Pipeline()

# Creates element by name

src_name = "my_video_test_src"
src = Gst.ElementFactory.make("videotestsrc")
src.set_property("num-buffers", 50)
src.set_property("pattern", "ball")


sink = Gst.ElementFactory.make("gtksink")

pipeline.add(src, sink)

src.link(sink)


bus = pipeline.get_bus() 

# allow bus to emit messages to main thread 
bus.add_signal_watch()

# Add handler to specific signal
bus.connect("message", on_message, None)

# Start pipeline
pipeline.set_state(Gst.State.PLAYING)

# Init GObject loop to handle Gstreamer Bus Events
loop = GObject.MainLoop()

try:
    loop.run()
except:
    traceback.print_exc()
    
# Stop Pipeline
pipeline.set_state(Gst.State.NULL)


