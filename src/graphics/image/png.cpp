#include <graphics/abstract/image.hpp>
#include <graphics/image/png.hpp>
#include <png.h>
#include <iostream>

namespace tung {

// class PngImage
PngImage::PngImage() {}

int PngImage::width() const { return width_; }

int PngImage::height() const { return height_; }

const void *PngImage::data() const { return data_; }

PngImage::Format PngImage::format() const {
    return format_;
}

IImage::BitDepth PngImage::bit_depth() const {
    return bit_depth_;
}


int PngImage::color_component_count() const {
    if (format_ == FORMAT_RGB)
        return 3;
    else if (format_ == FORMAT_RGBA) 
        return 4;
    return -1;
}

PngImage::~PngImage() {
    ::free(data_);
}

// class PngImageLoader
IImagePtr PngImageLoader::load(const std::string& filename) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
 
    if ((fp = fopen(filename.c_str(), "rb")) == NULL)
        throw ImageException("Can't read file");
 
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     nullptr, nullptr, nullptr);
 
    if (png_ptr == nullptr) {
        fclose(fp);
        throw ImageException("Can't load file");
    }
 
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw ImageException("Can't load file");
    }
 
    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        throw ImageException("Can't load file");
    }
 
    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
 
    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
 
    auto result = std::make_shared<PngImage>();

    png_read_png(png_ptr, info_ptr, 
            PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | 
            PNG_TRANSFORM_EXPAND, NULL);
 
    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, 
            &width, &height, &bit_depth, &color_type,
            &interlace_type, NULL, NULL);

    result->width_ = width;
    result->height_ = height;
    
    if (bit_depth == 8)
        result->bit_depth_ = IImage::BIT_DEPTH_8;
    else if (bit_depth == 16)
        result->bit_depth_ = IImage::BIT_DEPTH_16;
    else
        throw ImageException("Wrong bit depth");

    if (color_type == PNG_COLOR_TYPE_RGB)
        result->format_ = IImage::FORMAT_RGBA;
    else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
        result->format_ = IImage::FORMAT_RGBA;
    else
        throw ImageException("Wrong color type");
 
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    result->data_ = malloc(row_bytes * result->height_);
 
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
    for (int i = 0; i < result->height_; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy((unsigned char *)result->data_ + 
                (row_bytes * (result->height_ - 1 - i)), 
                row_pointers[i], row_bytes);
    }
 
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return result;
}

PngImageLoader::~PngImageLoader() {
}

} // namespace tung
