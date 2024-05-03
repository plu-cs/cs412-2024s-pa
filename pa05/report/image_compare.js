
window.addEventListener("DOMContentLoaded", main);

function main() {
    document.querySelectorAll(".img-compare").forEach( (el) => imageCompare(el) );
}

function imageCompare( container ) {
    const slider = document.createElement("div");
    slider.classList.add("img-compare-slider");
    container.appendChild( slider );
    const sliderDefaultOpacity = slider.style.opacity;

    const imageDiv = container.children;
    const firstImageDiv = imageDiv[0];
    const secondImageDiv = imageDiv[1];
    const width = firstImageDiv.clientWidth;
    const height = firstImageDiv.clientHeight;

    // Make the container the same height
    container.style.height = height + "px";

    // Make the second image container the same size as the first if it isn't already
    if( secondImageDiv.offsetWidth !== width ) secondImageDiv.style.width = width + "px";
    if( secondImageDiv.offsetWidth !== height ) secondImageDiv.style.height = height + "px";

    // Position slider in the center
    slider.style.top =  ((height / 2) - (slider.offsetHeight / 2)) + "px";
    slider.style.left = ((width / 2) - (slider.offsetWidth / 2)) + "px";

    // Set the first image to half width
    firstImageDiv.style.width = (width / 2) + "px";

    let dragging = false;

    const mouseMove = (e) => {
        if( !dragging ) return;

        // Get the x position of the mouse, relative to the first image
        const a = firstImageDiv.getBoundingClientRect();
        let x = e.pageX - a.left;
        x = x - window.scrollX;  // Consider horizontal scrolling

        // Prevent the slider from being positioned outside the image
        if (x < 0) x = 0;
        if (x > width) x = width;

        // Resize the image
        firstImageDiv.style.width = x + "px";
        // Position the slider
        slider.style.left = (firstImageDiv.offsetWidth - (slider.offsetWidth / 2)) + "px";
    };

    slider.addEventListener("mousedown", (e) => {
        e.preventDefault();
        slider.style.opacity = "0.33";
        dragging = true;
        window.addEventListener("mousemove", mouseMove);
    });
    
    window.addEventListener("mouseup", (e) => {
        dragging = false;
        slider.style.opacity = sliderDefaultOpacity;
        window.removeEventListener("mousemove", mouseMove);
    });
}