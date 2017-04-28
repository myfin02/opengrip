// Bateries 18560
// Centered
module bateries() {
    rotate([90, 0, 0]) {
        translate([-10, 0, 0]) {
            cylinder(h=62.5, r=9, center=true);
            translate([20, 0, 0])
            cylinder(h=62.5, r=9, center=true);
        }
    }
}

module bateryBoxWholes() {
    rotate([90, 0, 0]) {
        translate([-10, 0, 0]) {
            cylinder(h=72.5, r=1, center=true, $fn=15);
            translate([20, 0, 0])
            cylinder(h=72.5, r=1, center=true, $fn=15);
        }
    }
}


module bateryBox() {
    
    difference() {
        cube([44, 71.2, 20], center=true);
        translate([0, 22.8, 2]) {
            cube([45, 20.6, 20], center=true);
        }
        translate([0, -22.8, 2]) {
            cube([45, 20.6, 20], center=true);
        }
        bateries();
        translate([0, -1.8, 0])
            bateries();
        translate([0, 1.8, 0])
            bateries();
        translate([0, 0, 14]) {
            cube([45, 26, 20], center=true);
        }
            
        // Díry v dolní části (úpora materiálu)
        translate([0, -22.8, -10])
            cube([8, 20.6, 10], center=true);
        translate([20, -22.8, -10])
            cube([8, 20.6, 10], center=true);
        translate([-20, -22.8, -10])
            cube([8, 20.6, 10], center=true);
            
        // Díry v dolní části (śpora materiálu)
        translate([0, 22.8, -10])
            cube([8, 20.6, 10], center=true);
        translate([-20, 22.8, -10])
            cube([8, 20.6, 10], center=true);
        translate([20, 22.8, -10])
            cube([8, 20.6, 10], center=true);
        
        // díry na kontakty
        bateryBoxWholes();
        
        // odstranění hran
        translate([26, 35, -5])
            cube(14, 10, 10, center=true);
        translate([-26, 35, -5])
            cube(14, 10, 10, center=true);
        translate([26, -35, -5])
            cube(14, 10, 10, center=true);
        translate([-26, -35, -5])
            cube(14, 10, 10, center=true);
    }
}

module angler() {
    translate([0, 35, 0]) {
        difference() {
            cube([45, 10, 22], center=true);
            bateries();
            translate([0, 0, -10])
                cube([40, 11, 20], center=true);
            translate([0, 0, -4])
                cube([30, 11, 20], center=true);
        }
    }
    translate([0, -35, 0]) {
        difference() {
            cube([45, 10, 22], center=true);
            bateries();
            translate([0, 0, -10])
                cube([40, 11, 20], center=true);
            translate([0, 0, -4])
                cube([30, 11, 20], center=true);
        }
    }
}


//bateries();
difference() {
    bateryBox();
    angler();
}
