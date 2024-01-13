import { mount } from '@vue/test-utils';
import MapComponent from '@/components/MapComponent.vue';
import { JSDOM } from 'jsdom';

describe('MapComponent', () => {
    let wrapper;
    let map;
    beforeEach(async () => {
        const dom = new JSDOM('<!doctype html><html><body><div id="app"></div></body></html>');
        global.document = dom.window.document;
        global.window = dom.window;
        // Define the transformers prop data
        const transformers = [
            {
                parameters: {
                    current: 100,
                    voltage: 410,
                    power: 100 * 410,
                    operational: true
                },
                position: [32.5822, 0.818]
            },
            {
                parameters: {
                    current: 110,
                    voltage: 400,
                    power: 110 * 400,
                    operational: true
                },
                position: [32.5822, 0.618]
            }
        ];

        // Mount the component with the transformers prop
        wrapper = mount(MapComponent, {
            attachTo: document.getElementById('app'),
            props: {
                transformers
            }
        });

        // Wait for any asynchronous updates to complete
        await wrapper.vm.$nextTick();
        map = wrapper.vm.map;
        // console.log(wrapper.vm.map);
    });

    //interactive map specific functionality
    it('renders map container', () => {
        const container = wrapper.find("#map");
        expect(container.exists()).toBe(true);
    });

    it('centers map at the correct location', () => {
        const center = map.getCenter();
        expect(center.lat).toBeCloseTo(0.34759640);
        expect(center.lng).toBeCloseTo(32.58251970);
    });

    it('allows map to pan', () => {
        const centerBeforePanning = map.getCenter();
        map.panBy([100, 100]);
        expect(centerBeforePanning).not.toEqual(map.getCenter());
    });

    it('allows map to zoom in and out', () => {
        const initialZoom = map.getZoom();
        map.zoomIn();
        expect(map.getZoom()).toBeGreaterThan(initialZoom);
        map.zoomOut();
        map.zoomOut();
        expect(map.getZoom()).toBeLessThan(initialZoom);
    });

    it('renders the correct number of markers', () => {
        // Check that the number of markers matches the number of transformers
        expect(wrapper.vm.mapmarkers.length).toBe(wrapper.props().transformers.length);
        
    });

    it('renders markers at the correct positions', () => {
        // Check that each marker is at the correct position
        wrapper.vm.mapmarkers.forEach((marker, index) => {
            expect(marker.getLatLng()).toEqual(L.latLng(wrapper.props().transformers[index].position));
        });
    });

    it('renders markers with the correct icons', () => {
        // Check that each marker has the correct icon
        wrapper.vm.mapmarkers.forEach((marker, index) => {
            const expectedIconUrl = wrapper.props().transformers[index].parameters.operational ? '../../public/operationalIcon.png' : '../../public/faultyIcon.png';
            expect(marker.options.icon.options.iconUrl).toBe(expectedIconUrl);
        });
    });

    it('shows tooltip with brief information about the transformer on hover', () => {
        // Check that each marker's tooltip content matches the transformer's information
        wrapper.vm.mapmarkers.forEach((marker, index) => {
            const transformer = wrapper.props().transformers[index].parameters;
            const expectedTooltipContent = `Current: ${transformer.current}<br/>Voltage: ${transformer.voltage}<br/>Power: ${transformer.power}<br/>Status: ${transformer.operational ? 'Operational': 'Faulty'}`;
            expect(marker.getTooltip().getContent()).toBe(expectedTooltipContent);
        });
    });
});
