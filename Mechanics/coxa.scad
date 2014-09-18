// 3dof quad 
//
// coxa

include <servo.scad>
include <servo_arm.scad>

module coxa(servo_height = 27, servo_clearance = 7) {
	arm_thick = 4;
	servo_width = 12;
	flange_length = 3;
	base_thick = 4;
	root_radius = 4;

	fork_width = servo_width + flange_length + servo_clearance + base_thick;
	fork_height = arm_thick * 2 + servo_height;
	
	servo_cog_offset = 6;

	translate([fork_width/2 - servo_cog_offset, 0, 0]) union() {
		difference() {
			cube([fork_width, fork_height, 12], center = true);
			translate([-root_radius/2 - base_thick/2 - 1, 0, 0]) cube([1 + servo_width + flange_length + servo_clearance - root_radius, servo_height, 13], center = true);
			translate([-base_thick/2, 0, 0]) cube([servo_width + flange_length + servo_clearance, servo_height-2*root_radius, 13], center = true);
			translate([5, -9.5, 0]) cylinder(r = root_radius, h = 13, center = true);	
			translate([5, 9.5, 0]) cylinder(r = root_radius, h = 13, center = true);	
			color("white") translate([servo_cog_offset - fork_width/2, 0.1 + fork_height/2, 0]) rotate([90, 90, 0]) servo_arm();
		}

		translate([fork_width/2 + 15/2, 0, -3]) {
			difference() {	
				cube([15, fork_height, 6], center = true);
				translate([-1, 0, 0]) cube([12.5, 23.5, 7], center = true);
				for(i = [-1, 1]) {
					translate([-1, i * 28/2, 0]) cylinder(r=.75, h=20, center = true);
				}
				translate([-1, 12.25, 0]) cube([4, 1, 25], center = true);
				translate([-1, -12.25, 0]) cube([4, 1, 25], center = true);
			}
		}
	}

}

translate([0,15,0]) coxa(); 
scale([-1, 1, 1]) coxa();