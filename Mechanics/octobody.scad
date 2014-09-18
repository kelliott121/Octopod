include <singlehip.scad>;

octobody();

module octobody(hip_angle=30, hip_space=20)
{
	for (	quadrant = [[1,1],[1,-1],[-1,1],[-1,-1]])
	{
		for (	multiplier = [0.5, 1.5])
		{
			translate([	quadrant[0] * quadrant[1] * (15),
							quadrant[0] * (hip_space * multiplier),
							0])
			rotate([	0,
						0,
						quadrant[1] * (hip_angle * multiplier)])
			translate(	quadrant[0] * [quadrant[1] * 18,
							0,
							0])
			hip(23,12.5);
		}
	}
	
	translate([0,-(hip_space * 1.5 + 24)]) rotate([0,0,90]) hip(23,12.5);

	linear_extrude(height=4)
	polygon([
	[10,(hip_space * 1.5 + 9)],[10,(hip_space * 1.5 + 6)],
	[21,(hip_space * 1.5 - 5)],[24,(hip_space * 1.5 - 5)],
	[24,(hip_space * 0.5 + 11)],
	[21,(hip_space * 0.5 + 11)],
	[14,(hip_space * 0.5 + 8)],
	[19,(hip_space * 0.5 - 8)],
	[22,(hip_space * 0.5 - 8)],
	[22,-(hip_space * 0.5 - 8)],
	[19,-(hip_space * 0.5 - 8)],
	[14,-(hip_space * 0.5 + 8)],
	[21,-(hip_space * 0.5 + 11)],
	[24,-(hip_space * 0.5 + 11)],
	[24,-(hip_space * 1.5 - 5)],
	[21,-(hip_space * 1.5 - 5)],
	[10,-(hip_space * 1.5 + 6)],
	[10,-(hip_space * 1.5 + 9)],
	[-10,-(hip_space * 1.5 + 9)],
	[-10,-(hip_space * 1.5 + 6)],
	[-21,-(hip_space * 1.5 - 5)],
	[-24,-(hip_space * 1.5 - 5)],
	[-24,-(hip_space * 0.5 + 11)],
	[-21,-(hip_space * 0.5 + 11)],
	[-14,-(hip_space * 0.5 + 8)],
	[-19,-(hip_space * 0.5 - 8)],
	[-22,-(hip_space * 0.5 - 8)],
	[-22,(hip_space * 0.5 - 8)],
	[-19,(hip_space * 0.5 - 8)],
	[-14,(hip_space * 0.5 + 8)],
	[-21,(hip_space * 0.5 + 11)],
	[-24,(hip_space * 0.5 + 11)],
	[-24,(hip_space * 1.5 - 5)],
	[-21,(hip_space * 1.5 - 5)],
	[-10,(hip_space * 1.5 + 6)],
	[-10,(hip_space * 1.5 + 9)]
]);
}