
import tables


from tagselector import TagSelector


class SimulationResultTraces(object):
    def __init__(self, time_pts, data_pts):
        self.time_pts = time_pts
        self.data_pts = data_pts




class SimulationResultEventsProxy(object):
    def __init__(self,group):
        self.group = group
        self.tags = group._v_attrs['hdf-jive:tags'].split(",")
        assert len(group._v_children) == 1

        self.arr = group._v_children.values()[0]

    @property
    def evt_times(self):
        return self.arr[:,0]


class SimulationResultTraceProxy(object):

    def __init__(self, group):
        self.group = group
        self.tags = group._v_attrs['hdf-jive:tags'].split(",")
        #print self.tags

        # Check everything is OK:
        self.raw_data = SimulationResultTraces(
                    time_pts=group.raw.time().read(),
                    data_pts=group.raw.data.read(),
                    )



class HDF5SimulationResultFile(object):


    def __init__(self, filename):
        self.h5file = tables.openFile(filename)

        self.simulation_results_traces, self.simulation_results_events = self.find_hdf5_simulationresults()
        print 'Simulation Results found:' , len(self.simulation_results_traces), '/', len(self.simulation_results_events)




    def find_hdf5_simulationresults(self):

        hdfjive_trace_groups = []
        hdfjive_events_groups = []
        for array in self.h5file.walkNodes(classname="Group"):
            if 'hdf-jive' in array._v_attrs._v_attrnames:
                res_type = getattr( array._v_attrs, 'hdf-jive')

                if res_type=='trace':
                    hdfjive_trace_groups.append(array)
                elif res_type=='events':
                    hdfjive_events_groups.append(array)
                else:
                    assert False

        # Now, construct the SimulationResult objects:
        res_traces = [ SimulationResultTraceProxy(gr) for gr in hdfjive_trace_groups]
        res_events = [ SimulationResultEventsProxy(gr) for gr in hdfjive_events_groups]
        return res_traces, res_events



    def filter_traces(self, selector):
        if isinstance(selector, basestring):
            selector = TagSelector.from_string(selector)
        return selector.filter(self.simulation_results_traces)
    def filter_events(self, selector):
        if isinstance(selector, basestring):
            selector = TagSelector.from_string(selector)
        return selector.filter(self.simulation_results_events)





