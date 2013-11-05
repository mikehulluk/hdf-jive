 


# Plotting classes:
class RasterGroup(object):
    def __init__(self, name, subgroups):
        self.name = name
        self.subgroups = subgroups


class RasterSubgroup(object):
    def __init__(self, tagstring, mplkwargs):
        self.tagstring = tagstring
        self.mplkwargs = mplkwargs




