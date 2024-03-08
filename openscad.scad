
height = 50;
radius = 20;
levels = 5;
fin_height = 45; 
fin_width = 80; 
fin_length = 5; 


module createConeLike(h, r, level) {
    if (level == 0) {
        translate([0, 0, -h]) {
            cube([fin_length, fin_width, fin_height], center=true); 
        }
        
        cylinder(h, r, r, center=true);     } else {
        cylinder(h, r, r, center=true);
        
        nextHeight = h * 0.8;
        nextRadius = r * 0.8;
        
        translate([0, 0, h-5]) {
            createConeLike(nextHeight, nextRadius, level - 1);
        }
    }
}

rotate([0, 90, 0]) {
    createConeLike(height, radius, levels);
}
