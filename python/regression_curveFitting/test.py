#!/usr/bin/python
#-*- coding: utf-8 -*-

from pylab import *
from random import normalvariate
 
a = 0.03
b = 0.21
c = 0.4
f = lambda x,a=a,b=b,c=c:a*x**2+b*x+c
xList = arange(-10,10,0.25)
yListTrue = [f(x) for x in xList]
yListMeasured = [y+normalvariate(0,1) for y in yListTrue]


# fit the data
def polyFit(xList,yList,order=1):
    '''fit the data using a least squares and polynomial'''
    fList = [(lambda x,n=n: x**n) for n in range(order,-1,-1)]
    # build row for each element in y
    bList = []
    A_List = []
    for (thisX,thisY) in zip(xList,yList):
        bList.append(thisY)
        A_Row = [f(thisX) for f in fList]
        A_List.append(A_Row)
    b = matrix(bList).T
    A = matrix(A_List)
    w = inv(A.T*A)*A.T*b
    return w.T.tolist()[0]
     
w = polyFit(xList,yListMeasured,order=2)
aHat = w[0]
bHat = w[1]
cHat = w[2]
 
# summarize the results
print 'Data model is   :%4.2f*x^2 + %4.2f*x + %4.2f' % (a,b,c)
print 'Fit equation is :%4.2f*x^2 + %4.2f*x + %4.2f' % (aHat,bHat,cHat)
 
# plot, for visual comparison
def getPolyF(w):
    '''create a function using the fit values'''
    return lambda x,w=w: sum([thisW*(x**(len(w)-n-1)) 
                            for n,thisW in enumerate(w)])
 
fHat = getPolyF(w)
xPlotList = arange(-10,10,0.1)
yEstList = [fHat(x) for x in xPlotList]
fTrue = getPolyF([a,b,c])
yTrueList = [fTrue(x) for x in xPlotList]
 
figure(1)
plot(xPlotList,yEstList,'--g',linewidth=2)
plot(xPlotList,yTrueList,'b',linewidth=2)
plot(xList,yListMeasured,'+r',markersize = 12,markeredgewidth=2)
xlabel('x')
ylabel('y')
legend(['estimate','true','measured'])
grid(True)
savefig('secondOrderFitEx.png')
show()
