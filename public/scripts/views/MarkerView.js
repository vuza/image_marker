define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor'], function(markerView, Marionette, d3, randomColor) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function(opt){
            if(opt){
                if(opt.image) MarkerView.image = opt.image;
                if(opt.matrix) MarkerView.matrix = opt.matrix;
            }
        },

        onRender: function(){this.createSvg(); return this},

        attributes: function () {
            return {
                'id': 'markerView'
            }
        },

        createSvg: function(){
            var width = 960,
                height = 500;

            // create the svg
            var svg = d3.select(this.el).append("svg")
                .attr("width", width)
                .attr("height", height)
                .append("g");

            // add the image
            var defs = svg.append("defs");

            defs.append('pattern')
                .attr('id', 'image')
                .attr('patternUnits', 'userSpaceOnUse')
                .attr('width', width)
                .attr('height', height)
                .append('image')
                .attr('xlink:href', MarkerView.image)
                .attr('width', width)
                .attr('height', height);

            svg.append('rect')
                .attr('x', 0)
                .attr('y', 0)
                .attr('width', width)
                .attr('height', height)
                .attr('fill', 'url(#image)');

            svg.selectAll('.dot')
                .data(MarkerView.matrix)
                .enter().append('circle')
                .attr('class', 'dot')
                .attr('r', 1)
                .attr('cx', function(d) { return d.x; })
                .attr('cy', function(d) { return d.y; })
                .style('fill', function(){ return randomColor({
                    format: 'hex'
                }); })
                .attr('fill-opacity', function(){ return Math.random() * (1 - 0.2) + 0.2; });
        }
    });

    return MarkerView;
});