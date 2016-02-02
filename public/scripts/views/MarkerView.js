define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor'], function(markerView, Marionette, d3, randomColor) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function(image){
            this.image = image;
            console.log(image.attributes);
        },

        onRender: function(){this.createSvg(); return this},

        attributes: function () {
            return {
                'id': 'markerView'
            }
        },

        createSvg: function(){
            // create the svg
            var svg = d3.select(this.el).append("svg")
                .attr('width', this.image.get('width'))
                .attr('height', this.image.get('height'))
                .append("g");

            // add the image
            var defs = svg.append("defs");

            defs.append('pattern')
                .attr('id', 'image')
                .attr('patternUnits', 'userSpaceOnUse')
                .attr('width', this.image.get('width'))
                .attr('height', this.image.get('height'))
                .append('image')
                .attr('xlink:href', '/images/' + this.image.get('name'))
                .attr('width', this.image.get('width'))
                .attr('height', this.image.get('height'));

            svg.append('rect')
                .attr('x', 0)
                .attr('y', 0)
                .attr('width', this.image.get('width'))
                .attr('height', this.image.get('height'))
                .attr('fill', 'url(#image)');

            svg.selectAll('.dot')
                .data(this.image.get('matrix'))
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