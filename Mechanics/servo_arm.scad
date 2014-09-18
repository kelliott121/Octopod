//servo_arm();

module servo_arm(body_r = 7.5/2, arm_r1 = 6/2, arm_r2 = 4/2, arm_len = 15, arm_t = 2, body_t = 5) {
	cylinder(r = body_r, h = body_t);
	
	linear_extrude(height = arm_t) {
		circle(r = arm_r1);
		translate([0,arm_len,0]) circle(r = arm_r2);
		polygon(points = [ [-arm_r1, 0], [arm_r1, 0], [arm_r2, arm_len], [-arm_r2, arm_len] ]);
	}
}