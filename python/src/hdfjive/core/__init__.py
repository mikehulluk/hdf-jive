
import os


import tables

import itertools as it

from hdfjive.tagselection import TagSelector

class SimulationResultTraces(object):
    def __init__(self, node):
        self.node = node
        self._time_pts=None
        self._data_pts=None

    @property
    def time_pts(self):
        if self._time_pts is None:

            # Dereference this, because its actually a soft-link:
            time_node = self.node.time()

            sf = time_node._v_attrs.__dict__.get("hdfjive:scaling", None)
            assert sf is not None
            self._time_pts  = time_node.read() * sf
        return self._time_pts

    @property
    def data_pts(self):
        if self._data_pts is None:
            sf = self.node.data._v_attrs.__dict__.get("hdfjive:scaling", 1.0)
            assert sf is not None
            self._data_pts  = self.node.data.read() * sf
        return self._data_pts





class SimulationResultEventsProxy(object):
    def __init__(self,group):
        self.group = group
        self.tags = [t.strip() for t in group._v_attrs['hdf-jive:tags'].split(",")]

        self.times_node = group._f_getChild("times")
        self._times = None


    @property
    def times(self):
        if self._times is None:
            sf = self.times_node._v_attrs.__dict__.get("hdfjive:scaling", 1.0)
            self._times = self.times_node.read() * sf
        return self._times

    def __len__(self):
        return len(self.times)


class SimulationResultTraceProxy(object):

    def __init__(self, group):
        self.group = group
        self.tags = [t.strip() for t in group._v_attrs['hdf-jive:tags'].split(",")]

        # Check everything is OK:
        self.raw_data = SimulationResultTraces(node=group.raw)






class HDF5SimulationResultFileSet(object):
    def __init__(self, input_):

        self.results_files = None

        if isinstance(input_, list):
            self.results_files = [HDF5SimulationResultFile.load(f) for f in input_]
        else:
            self.results_files = [HDF5SimulationResultFile.load(input_)]


    def filter_traces(self, selector):
        return list(it.chain( *[f.filter_traces(selector) for f in self.results_files] ) )

    def filter_events(self, selector):
        return list(it.chain( *[f.filter_events(selector) for f in self.results_files] ) )





    def plot(self, trace_filters=None, spike_filters=None, xlim=None, ylim=None, legend=False, xlabel=None, xscale=None, fig_trace_kwargs=None, fig_event_kwargs=None):
        import pylab
        import mreorg
        import numpy as np

        trace_filters = trace_filters or []
        spike_filters = spike_filters or []

        fig_trace_kwargs = fig_trace_kwargs or {}
        fig_event_kwargs = fig_event_kwargs or {}

        tr_figs = []
        for filt in trace_filters:
            fig = pylab.figure(**fig_trace_kwargs)
            tr_figs.append(fig)

            trs = self.filter_traces(filt)


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


        spike_figs = []
        for filt in spike_filters:
            f2 = pylab.figure(**fig_event_kwargs)
            spike_figs.append(f2)
            #trs = self.filter_events(filt)
            trs = list(it.chain( *[f.filter_events(filt) for f in self.results_files] ) )
            trs = self.filter_events(filt)
            print ' -- plotting:', filt, len(trs)
            for i,res in enumerate(trs):
                evt_times = res.times

                pylab.plot( evt_times, i+ 0*evt_times, 'x', label=','.join(res.tags))
            if xlim:
                pylab.xlim(*xlim)
            pylab.ylabel(filt)
            if legend:
                pylab.legend()
            if ylim:
                pylab.ylim(*ylim)
            else:
                pylab.ylim(0, len(trs))
            mreorg.PM.save_active_figures()

        return tr_figs, spike_figs


    def raster_plot(self, raster_groups, xlim=None, fig_kwargs=None, legend=False):
        print 'Plotting Raster'
        import pylab
        import mreorg
        import numpy as np

        fig_kwargs = fig_kwargs or {}

        group_separation = 5

        f = pylab.figure(**fig_kwargs)
        f.subplots_adjust(bottom=0.2,hspace=0.05)

        # Lets set 0 at the top, and working down:



        for rgi, rg in enumerate(raster_groups):
            #print 'Plotting Raster (%s)' % rg.name
            ax = f.add_subplot(len(raster_groups),1,rgi+1)
            ax.invert_yaxis()
            legend_data = []

            n_objs = None
            for sg in rg.subgroups:
                evtsset = [evproxy.times for evproxy in self.filter_events(sg.tagstring)]

                #print ' --', sg


                # Sanity Checking!
                if n_objs is None:
                    n_objs = len(evtsset)
                else:
                    #assert n_objs==len(evtsset)
                    pass

                for i,evts in enumerate(evtsset):
                    kwargs = {'marker':'x' }
                    kwargs.update(sg.mplkwargs)

                    l = ax.scatter( evts, np.ones_like(evts) * i, **kwargs)

                legend_data.append( (l,sg.label) )

            if legend:
                ax.legend( *zip(*legend_data) )

            ax.set_ylabel(rg.name)

            if(rgi != len(raster_groups) -1 ):
                ax.set_xticklabels('')




            if xlim:
                pylab.xlim(*xlim)

            #5% margins:
            margin = float(n_objs) * 0.10
            pylab.ylim(n_objs+margin,0-margin)


        return f
        pylab.show()







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

        res_traces.sort(key=lambda o:o.group._v_pathname)
        res_events.sort(key=lambda o:o.group._v_pathname)
        return res_traces, res_events



    def filter_traces(self, selector):
        if isinstance(selector, basestring):
            selector = TagSelector.from_string(selector)
        return selector.filter(self.simulation_results_traces)
    def filter_events(self, selector):
        if isinstance(selector, basestring):
            selector = TagSelector.from_string(selector)
        return selector.filter(self.simulation_results_events)



    def plot(self, *args, **kwargs):
        return HDF5SimulationResultFileSet(self).plot(*args, **kwargs)
    def raster_plot(self, *args, **kwargs):
        return HDF5SimulationResultFileSet(self).raster_plot(*args, **kwargs)


    def find_eventsets(self, tag_selection, min_spikes=1):
        evtsets = self.filter_events(tag_selection)
        valid_evtsets = []
        for evtset in evtsets:
            if len(evtset) > min_spikes:
                valid_evtsets.append(evtset)
        return valid_evtsets




