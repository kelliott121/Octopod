tibia();

module tibia(sl = 23, sw = 12.5){
	difference(){
		//solid parts
		union(){
			hull(){
				//main inner square
				translate([-30,-10,0]) cube([28,20,4]);
				//lower taper
				translate([5,-1.5,0]) cube([2,3,4]);
			}
	
			//leg
			translate([0,-1.5,0]) cube([40,3,4]);
			//top bar
			translate([-33,-7,0]) cube([6,14,4]);
			//rounded corners
			for (i = [ [-30,7,0],[-30,-7,0] ]){
				translate(i) cylinder(r=3,h=4,$fn=50);
			}	
		}
		//servo mounts
		for (i = [ [-3,0,-2],[-31,0,-2] ]){
			translate(i) cylinder(r=1,h=20,$fn=20);
		}
		//hole for servo body
		translate([-17,0,2])  cube([sl,sw,22], center=true);
		
		// hole for servo wires
		translate([-5,0,2]) cube([1,4,10], center=true);
		translate([-29,0,2]) cube([1,4,10], center=true);	
	}
}


