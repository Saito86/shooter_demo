
fn exportMesh fname = 
(
	if $selection.count != 1 then
	(
		print "Select the mesh"
		return 0
	)
	animStart = animationRange.start
	animEnd = animationRange.end
	frameCount = animEnd - animStart + 1
	--print frameCount
	currFrame = animStart
	sliderTime = currFrame
	f = fopen fname "wb"
	obj = $selection[1]
	tmesh = snapshotAsMesh obj
	vc = tmesh.numverts
	fc = tmesh.numfaces
	--header
	writelong f vc
	writelong f fc
	writelong f frameCount
	--faces
	for v=1 to fc do
	(
		face = getFace tmesh v
		x = face.x
		xx = x as Integer
		xx = xx-1
		
		y = face.y
		yy = y as Integer
		yy = yy-1
		
		z = face.z
		zz = z as Integer
		zz = zz-1
		
		writelong f xx
		writelong f yy
		writelong f zz
		
		tface = getTVFace tmesh v
		v1 = getTVert tmesh tface.x
		v2 = getTVert tmesh tface.y
		v3 = getTVert tmesh tface.z
		
		t1x = v1.x
		t1y = 1-v1.y
		t2x = v2.x
		t2y = 1-v2.y
		t3x = v3.x
		t3y = 1-v3.y
		
		writefloat f t1x
		writefloat f t1y
		writefloat f t2x
		writefloat f t2y
		writefloat f t3x
		writefloat f t3y
	)
	delete tmesh
	--frames
	for i=animStart to animEnd do
	(
		slidertime = i
		tmesh = snapshotAsMesh obj
		for v=1 to vc do
		(
			vert = getVert tmesh v
			writefloat f -vert.x
			writefloat f vert.z
			writefloat f vert.y
			
			norm = getNormal tmesh v
			n = norm/(length norm)
			writefloat f n.x
			writefloat f n.z
			writefloat f n.y
		)
		delete tmesh
	)
	slidertime = animStart
	--cleanup
	fclose f
	print "OK"
)

utility exportAniMesh "AM Exporter"
(
	group "Export Mesh"
	(
		button bExportMesh " Export "
	)
	
	on bExportMesh pressed do
	(
		fname = getsavefilename caption:"Save SAM" types:"SAM(*.sam)|*.sam|All Files(*.*)|*.*|"
		--fname = "test.sam"
		exportMesh(fname)
	)
)