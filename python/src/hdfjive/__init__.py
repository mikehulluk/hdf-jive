
import tables


from tagselector import TagSelector


class SimulationResultTraces(object):
    def __init__(self, time_pts, data_pts):
        self.time_pts = time_pts
        self.data_pts = data_pts





class SimulationResultTraceProxy(object):


    def __init__(self, group):
        self.group = group
        self.tags = group._v_attrs['hdf-jive:tags'].split(",")
        print self.tags

        # Check everything is OK:
        self.raw_data = SimulationResultTraces(
                    time_pts=group.raw.time().read(),
                    data_pts=group.raw.data.read(),
                    )



class HDF5SimulationResultFile(object):


    def __init__(self, filename):
        self.h5file = tables.openFile(filename)

        print 'OK'


        self.simulation_results = self.find_hdf5_simulationresults()
        print 'Simulation Results found:' , len(self.simulation_results)




    def find_hdf5_simulationresults(self):

        hdfjive_groups = []
        for array in self.h5file.walkNodes(classname="Group"):
            if 'hdf-jive' in array._v_attrs._v_attrnames:
                hdfjive_groups.append(array)

        # Now, construct the SimulationResult objects:
        res = [ SimulationResultTraceProxy(gr) for gr in hdfjive_groups]
        return res

    def filter(self, selector):
        if isinstance(selector, basestring):
            selector = TagSelector.from_string(selector)

        return selector.filter(self.simulation_results)
        #for res in self.simulation_results:






    #def get_traces():
    #    pass
    #
    #def get_trace(self):
    #    pass
