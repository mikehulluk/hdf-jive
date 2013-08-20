









import ply





class TagSelector(object):

    def __call__(self, tr):
        raise NotImplementedError()

    @classmethod
    def from_string(cls, s):
        from tagselectorstringparser import parse_tagselector_string
        return parse_tagselector_string(s)

    def filter(self, traces):
        return [trace for trace in traces if self.__call__(trace)]

    # Operator Overloading:
    def __and__(self, rhs):
        assert isinstance(rhs, TagSelector)
        return TagSelectorAnd(lhs=self, rhs=rhs)

    def __or__(self, rhs):
        assert isinstance(rhs, TagSelector)
        return TagSelectorOr(lhs=self, rhs=rhs)

    def select(self, trs):
        return [trace for trace in trs if self(trace)]


class TagSelectorAny(TagSelector):

    def __init__(self, tags):
        super(TagSelectorAny, self).__init__()
        self.tags = set(tags)

    def __call__(self, tr):
        return not set(self.tags).isdisjoint(tr.tags)


class TagSelectorAll(TagSelector):

    def __init__(self, tags):
        super(TagSelectorAll, self).__init__()
        self.tags = set(tags)

    def __call__(self, tr):
        return self.tags.issubset(set(tr.tags))


class TagSelectorBinary(TagSelector):

    def __init__(self, lhs, rhs):
        super(TagSelectorBinary, self).__init__()
        self.lhs = lhs
        self.rhs = rhs
    def __call__(self, tr):
        raise NotImplementedError()


class TagSelectorOr(TagSelectorBinary):

    def __call__(self, tr):
        return self.lhs(tr) or self.rhs(tr)


class TagSelectorAnd(TagSelectorBinary):

    def __call__(self, tr):
        return self.lhs(tr) and self.rhs(tr)


class TagSelectorNot(TagSelector):

    def __init__(self, rhs):
        super(TagSelectorNot, self).__init__()
        self.rhs = rhs

    def __call__(self, tr):
        return not self.rhs(tr)


class TagSelect(TagSelectorAll):

    def __init__(self, s):
        assert isinstance(s, basestring)
        super(TagSelect, self).__init__(tags=[s])






#class PredAnd(object):
#    pass
#
#
#class PredOr(object):
#    pass
#
#class PredNot(object):
#    pass
#
#class PredAll(object):
#    pass
#
#class PredAny(object):
#    pass

