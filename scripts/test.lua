-- test
print("test.lua loaded")

function testOnInit(self)
	a = getName(self)
	print(a)
	px,py,pz = getPos(self)
	rx,ry,rz = getRot(self)
	print(px,py,pz)
	print(rx,ry,rz)
	print(a,"initialized")
end

function testOnUpdate(self)
	a,b,c = getPos(self)
	d,e,f = getCamPos()
	dx,dy,dz = getDirection(a,b,c,d,e,f)
	dirX,dirY,dirZ = normalize(dx,dy,dz)
	--setPos(self,dirX*0.01,0.01,dirZ*0.01)
end

function testOnRender(self)
	--print("on render")
end

function testOnCleanup(self)
	a = getName(self)
	print("cleaning up:",a)
end
