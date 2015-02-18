
print("default.lua loaded")


function OnInit(self)

end

function OnUpdate(self)
	a,b,c = getPos(self)
	d,e,f = getCamPos()
	dx,dy,dz = getDirection(a,b,c,d,e,f)
	dirX,dirY,dirZ = normalize(dx,dy,dz)
	--moveTo(self,dirX,0.05,dirZ);
	if getDistance(a,b,c,d,e,f) < 2 then
		--moveTo(self,0,1,0)
	end
end

function OnCleanup(self)

end
