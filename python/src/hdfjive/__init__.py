
import tables


from tagselector import TagSelector
from itertools import chain
import os


class SimulationResultTraces(object):
    def __init__(self, node):

        self.node = node

        self._time_pts=None
        self._data_pts=None

    @property
    def time_pts(self):
        if self._time_pts is None:
            sf = self.node.time._v_attrs.__dict__["hdfjive:scaling"] if "hdfjive:scaling" in self.node.time._v_attrs.__dict__ else 1.0
            self._time_pts  = self.node.time().read() * sf
        return self._time_pts
        
    @property
    def data_pts(self):
        if self._data_pts is None:
            sf = self.node.data._v_attrs.__dict__["hdfjive:scaling"] if "hdfjive:scaling" in self.node.data._v_attrs.__dict__ else 1.0
            self._data_pts  = self.node.data.read() * sf
        return self._data_pts

            



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

        # Check everything is OK:
        self.raw_data = SimulationResultTraces(node=group.raw)






class HDF5SimulationResultFileSet(object):
    def __init__(self, input_):

        self.results_files = None

        if isinstance(input_, list):
            self.results_files = [HDF5SimulationResultFile.load(f) for f in input_]
        else:
            self.results_files = [HDF5SimulationResultFile.load(input_)]



    #def plot_all_comparisons(self, tag_filter_general, tag_filter1,):




    def plot(self, trace_filters=None, spike_filters=None, xlim=None, ylim=None, legend=False, xlabel=None, xscale=None):
        import pylab
        import mreorg
        import numpy as np

        trace_filters = trace_filters or []
        spike_filters = spike_filters or []

        for filt in trace_filters:
            #pylab.figure(figsize=(20,16))
            fig = pylab.figure()

            trs = list(chain( *[f.filter_traces(filt) for f in self.results_files] ) )


            print 'Plotting:', filt, len(trs)
            for res in trs:
                if xlim:
                    time_mask = np.logical_and(
                                    res.raw_data.time_pts>xlim[0],
                                    res.raw_data.time_pts<xlim[1],
                            )
                    time, data = res.raw_data.time_pts[time_mask], res.raw_data.data_pts[time_mask]
                else:
                    time, data = res.raw_data.time_pts, res.raw_data.data_pts

                if xscale is not None:
                    time = time * xscale
                pylab.plot(time, data,'x-', label=','.join(res.tags), ms=2 )

            if len(trs)==0:
                pylab.close(fig)

            else:
                pylab.ylabel(filt)
                if legend:
                    pylab.legend()

                if ylim:
                    pylab.ylim(*ylim)
                else:
                    pylab.autoscale(axis='y')
                if xlabel is not None:
                    pylab.xlabel(xlabel)

                mreorg.PM.save_figure(figname=filt)
                mreorg.PM.save_active_figures()


        for filt in spike_filters:
            pylab.figure(figsize=(20,16))
            #trs = self.filter_events(filt)
            trs = list(chain( *[f.filter_events(filt) for f in self.results_files] ) )
            print ' -- plotting:', filt, len(trs)
            for i,res in enumerate(trs):
                evt_times = res.evt_times
                
                pylab.plot( evt_times, i+ 0*evt_times, 'x', label=','.join(res.tags))
            if xlim:
                pylab.xlim(*xlim)
            pylab.ylabel(filt)
            if legend:
                pylab.legend()
            if ylim:
                pylab.ylim(*ylim)
            mreorg.PM.save_active_figures()








class HDF5SimulationResultFile(object):


    @classmethod
    def load(cls, src):
        if isinstance(src, HDF5SimulationResultFile):
            return src
        else:
            return HDF5SimulationResultFile(src)

    def __init__(self, filename):
        self.h5file = tables.openFile( (os.path.expanduser( filename) ) )

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



    def plot(self, **kwargs):
        HDF5SimulationResultFileSet(self).plot(**kwargs)




