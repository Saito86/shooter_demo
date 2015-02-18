fn exportMap fname = 
(
	f = createfile fname
	--write material names
	format "//%\n" fname to:f
	mat = getMeditMaterial 1
	for i = 1 to mat.numsubs do
	(
		format "mt %\n" mat[i].name to:f
	)
	
	if $selection.count == 0 then
	(
		actionMan.executeAction 0 "40021"  -- Selection: Select All
	)
	
	modpanel.addModToSelection (VertexPaint ()) ui:on
	macros.run "Modifier Stack" "Convert_to_Poly"
	--write map
	for i=1 to $selection.count do
	(
		obj = $selection[i]
		tmesh = snapshotAsMesh obj
		nm =obj.name
		vc = tmesh.numverts
		ic = tmesh.numfaces
		format "m % % %\n" vc ic nm to:f
		for v=1 to tmesh.numverts do
		(
			vert = getVert tmesh v
			col = getVertColor tmesh v
			r = col.r as Integer
			g = col.g as Integer
			b = col.b as Integer
			norm = getNormal tmesh v
			n = norm/(length norm)
			format "v % % % % % % % % %\n" -vert.x vert.z vert.y n.x n.z n.y r g b to:f
		)
		for v=1 to tmesh.numfaces do
		(
			face = getFace tmesh v
			
			x = (face.x as Integer)
			xx = x-1
			
			y = (face.y as Integer)
			yy = y-1
			
			z = (face.z as Integer)
			zz = z-1
			
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
			
			mid = getFaceMatID tmesh v
			
			format "f % % % % % % % % % %\n" xx yy zz t1x t1y t2x t2y t3x t3y mid to:f
		)
		format "\n" to:f
		delete tmesh
	)
	format "//end" to:f
	close f
	clearSelection()
	print "SUCCES"
)

utility export "Map Exporter"
(
	group "Export Map"
	(
		button bExportMesh " Export "
	)
	
	on bExportMesh pressed do
	(
		fname = getsavefilename caption:"Save SMP" types:"SMP(*.smp)|*.smp|All Files(*.*)|*.*|"
		--fname = "test.smp"
		exportMap(fname)
	)
)