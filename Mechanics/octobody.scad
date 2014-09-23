include <singlehip.scad>;

octobody();

module octobody(hip_angle=30, hip_space=25, hip_width=20)
{
	for (	quadrant = [[1,1],[1,-1],[-1,1],[-1,-1]])
	{
		for (	multiplier = [0.5, 1.5])
		{
			translate([	quadrant[0] * quadrant[1] * (hip_width),
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
	[(hip_width - 5),(hip_space * 1.5 + 9)],
	[(hip_width - 5),(hip_space * 1.5 + 6)],
	[(hip_width + 6),(hip_space * 1.5 - 5)],
	[(hip_width + 9),(hip_space * 1.5 - 5)],
	[(hip_width + 9),(hip_space * 0.5 + 11)],
	[(hip_width + 6),(hip_space * 0.5 + 11)],
	[(hip_width - 1),(hip_space * 0.5 + 8)],
	[(hip_width + 4),(hip_space * 0.5 - 8)],
	[(hip_width + 7),(hip_space * 0.5 - 8)],
	[(hip_width + 7),-(hip_space * 0.5 - 8)],
	[(hip_width + 4),-(hip_space * 0.5 - 8)],
	[(hip_width - 1),-(hip_space * 0.5 + 8)],
	[(hip_width + 6),-(hip_space * 0.5 + 11)],
	[(hip_width + 9),-(hip_space * 0.5 + 11)],
	[(hip_width + 9),-(hip_space * 1.5 - 5)],
	[(hip_width + 6),-(hip_space * 1.5 - 5)],
	[(hip_width - 5),-(hip_space * 1.5 + 6)],
	[(hip_width - 5),-(hip_space * 1.5 + 9)],
	[-(hip_width - 5),-(hip_space * 1.5 + 9)],
	[-(hip_width - 5),-(hip_space * 1.5 + 6)],
	[-(hip_width + 6),-(hip_space * 1.5 - 5)],
	[-(hip_width + 9),-(hip_space * 1.5 - 5)],
	[-(hip_width + 9),-(hip_space * 0.5 + 11)],
	[-(hip_width + 6),-(hip_space * 0.5 + 11)],
	[-(hip_width - 1),-(hip_space * 0.5 + 8)],
	[-(hip_width + 4),-(hip_space * 0.5 - 8)],
	[-(hip_width + 7),-(hip_space * 0.5 - 8)],
	[-(hip_width + 7),(hip_space * 0.5 - 8)],
	[-(hip_width + 4),(hip_space * 0.5 - 8)],
	[-(hip_width - 1),(hip_space * 0.5 + 8)],
	[-(hip_width + 6),(hip_space * 0.5 + 11)],
	[-(hip_width + 9),(hip_space * 0.5 + 11)],
	[-(hip_width + 9),(hip_space * 1.5 - 5)],
	[-(hip_width + 6),(hip_space * 1.5 - 5)],
	[-(hip_width - 5),(hip_space * 1.5 + 6)],
	[-(hip_width - 5),(hip_space * 1.5 + 9)]
]);
}