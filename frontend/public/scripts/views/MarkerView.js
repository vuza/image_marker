define(['tpl!templates/markerView.tpl', 'Marionette', 'd3'], function(markerView, Marionette, d3) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function(){
            var scaleX = d3.scale.linear()
                .domain([-30,30])
                .range([0,600]);

            var scaleY = d3.scale.linear()
                    .domain([0,50])
                    .range([500,0]);

            // create the svg
            var margin = {top: 20, right: 20, bottom: 30, left: 40},
                width = 960 - margin.left - margin.right,
                height = 500 - margin.top - margin.bottom;

            var svg = d3.select("body").append("svg")
                .attr("width", width + margin.left + margin.right)
                .attr("height", height + margin.top + margin.bottom)
                .append("g")
                .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

            // first test polygon
            var points = [{"x":0.0, "y":25.0},
                {"x":8.5,"y":23.4},
                {"x":13.0,"y":21.0},
                {"x":19.0,"y":15.5}];

            svg.append("polygon")
                .attr("stroke","black")
                .attr("stroke-width",2)
                .attr("points",function(d) {
                    return points.map(function(d) {
                        return [scaleX(d.x), scaleY(d.y)].join(",");
                    }).join(" ");
                });
        }
    });

    return MarkerView;
});